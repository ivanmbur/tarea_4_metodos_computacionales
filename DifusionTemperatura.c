#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mod(int i, int j);

void main(void)
{
	/*Se definen las variables del problema*/

	float nu = 1.0;
	float T[100][100];
	float T_pasado[100][100];	
	float dx = 1;
	float dt = 0.25;
	float r = dt*nu/(dx*dx);
	int i;
	int j;
	int n;

	/*Caso 1*/

	/*Condiciones de frontera abiertas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *abierta_1_0 = fopen("abierta_1_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(abierta_1_0, "%f ", T[i][j]);
		}
		fprintf(abierta_1_0, "\n");
	}
	fclose(abierta_1_0);

	FILE *abierta_1_promedio = fopen("abierta_1_promedio.txt", "w");
	float promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(abierta_1_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		T[0][0] = T_pasado[0][0] + r*(2*T_pasado[0][1] + 2*T_pasado[1][0] - 4*T_pasado[0][0]);
		T[0][100] = T_pasado[0][100] + r*(2*T_pasado[0][99] + 2*T_pasado[1][100] - 4*T_pasado[0][100]);
		T[100][0] = T_pasado[100][0] + r*(2*T_pasado[100][1] + 2*T_pasado[99][0] - 4*T_pasado[100][0]);
		T[100][100] = T_pasado[0][0] + r*(2*T_pasado[100][99] + 2*T_pasado[99][100] - 4*T_pasado[100][100]);
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				if((i>0) && (i<100) && (j>0) && (j<100))
				{
					T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
				}
				if((i==0) && (j>0) && (j<100))
				{
					T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + 2*T_pasado[i+1][j] - 4*T_pasado[i][j]);
				}
				if((i==100) && (j>0) && (j<100))
				{	
					T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + 2*T_pasado[i-1][j] - 4*T_pasado[i][j]);
				}
				if((j==0) && (i>0) && (i<100))
				{
					T[i][j] = T_pasado[i][j] + r*(2*T_pasado[i][j+1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
				}
				if((j==100) && (i>0) && (i<100))
				{
					T[i][j] = T_pasado[i][j] + r*(2*T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
				}
				promedio += T[i][j];
			}
		}
		
		promedio = promedio/(100*100);
		fprintf(abierta_1_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *abierta_1_100 = fopen("abierta_1_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(abierta_1_100, "%f ", T[i][j]);
				}
				fprintf(abierta_1_100, "\n");
			}
			fclose(abierta_1_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *abierta_1_2500 = fopen("abierta_1_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(abierta_1_2500, "%f ", T[i][j]);
				}
				fprintf(abierta_1_2500, "\n");
			}
			fclose(abierta_1_2500);
		}
	}
	fclose(abierta_1_promedio);
 
	/*Condiciones de frontera periodicas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *animacion = fopen("animacion_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(animacion, "%f ", T[i][j]);
		}
		fprintf(animacion, "\n");
	}
	fclose(animacion);

	FILE *periodica_1_0 = fopen("periodica_1_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(periodica_1_0, "%f ", T[i][j]);
		}
		fprintf(periodica_1_0, "\n");
	}
	fclose(periodica_1_0);

	FILE *periodica_1_promedio = fopen("periodica_1_promedio.txt", "w");
	promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(periodica_1_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T[i][j] = T_pasado[i][j] + r*(T_pasado[i][mod(j+1, 100)] + T_pasado[i][mod(j-1,100)] + T_pasado[mod(i+1,100)][j] + T_pasado[mod(i-1,100)][j] - 4*T_pasado[i][j]);
				promedio += T[i][j];
			}
		}
	
		if(((n+1) % 50) == 0) 
		{
			FILE *animacion = fopen("animacion_%f.txt", (n+1)*dt, "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(animacion, "%f ", T[i][j]);
				}
				fprintf(animacion, "\n");
			}
			fclose(animacion);
		}
	
		promedio = promedio/(100*100);
		fprintf(periodica_1_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *periodica_1_100 = fopen("periodica_1_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(periodica_1_100, "%f ", T[i][j]);
				}
				fprintf(periodica_1_100, "\n");
			}
			fclose(periodica_1_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *periodica_1_2500 = fopen("periodica_1_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(periodica_1_2500, "%f ", T[i][j]);
				}
				fprintf(periodica_1_2500, "\n");
			}
			fclose(periodica_1_2500);
		}
	}
	
	fclose(animacion);
	fclose(periodica_1_promedio);
	
	/*Condiciones de frontera fijas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *fija_1_0 = fopen("fija_1_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(fija_1_0, "%f ", T[i][j]);
		}
		fprintf(fija_1_0, "\n");
	}
	fclose(fija_1_0);

	FILE *fija_1_promedio = fopen("fija_1_promedio.txt", "w");
	promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(fija_1_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		for(i=1;i<99;i++)
		{
			for(j=1;j<99;j++)
			{
			T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
			}
		}
		
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				promedio += T[i][j];
			}
		}
		promedio = promedio/(100*100);
		fprintf(fija_1_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *fija_1_100 = fopen("fija_1_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(fija_1_100, "%f ", T[i][j]);
				}
				fprintf(fija_1_100, "\n");
			}
			fclose(fija_1_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *fija_1_2500 = fopen("fija_1_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(fija_1_2500, "%f ", T[i][j]);
				}
				fprintf(fija_1_2500, "\n");
			}
			fclose(fija_1_2500);
		}
	}
	fclose(fija_1_promedio);

	/*Caso 2*/

	/*Condiciones de frontera abiertas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *abierta_2_0 = fopen("abierta_2_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(abierta_2_0, "%f ", T[i][j]);
		}
		fprintf(abierta_2_0, "\n");
	}
	fclose(abierta_2_0);

	FILE *abierta_2_promedio = fopen("abierta_2_promedio.txt", "w");
	promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(abierta_2_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		T[0][0] = T_pasado[0][0] + r*(2*T_pasado[0][1] + 2*T_pasado[1][0] - 4*T_pasado[0][0]);
		T[0][100] = T_pasado[0][100] + r*(2*T_pasado[0][99] + 2*T_pasado[1][100] - 4*T_pasado[0][100]);
		T[100][0] = T_pasado[100][0] + r*(2*T_pasado[100][1] + 2*T_pasado[99][0] - 4*T_pasado[100][0]);
		T[100][100] = T_pasado[0][0] + r*(2*T_pasado[100][99] + 2*T_pasado[99][100] - 4*T_pasado[100][100]);
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				if(!((i>=20) && (i<40) && (j>=40) && (j<60)))
				{
					if((i>0) && (i<100) && (j>0) && (j<100))
					{
						T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
					}
					if((i==0) && (j>0) && (j<100))
					{
						T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + 2*T_pasado[i+1][j] - 4*T_pasado[i][j]);
					}
					if((i==100) && (j>0) && (j<100))
					{	
						T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + 2*T_pasado[i-1][j] - 4*T_pasado[i][j]);
					}
					if((j==0) && (i>0) && (i<100))
					{
						T[i][j] = T_pasado[i][j] + r*(2*T_pasado[i][j+1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
					}
					if((j==100) && (i>0) && (i<100))
					{
						T[i][j] = T_pasado[i][j] + r*(2*T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
					}
				}
				promedio += T[i][j];
			}
		}
		
		promedio = promedio/(100*100);
		fprintf(abierta_2_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *abierta_2_100 = fopen("abierta_2_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(abierta_2_100, "%f ", T[i][j]);
				}
				fprintf(abierta_2_100, "\n");
			}
			fclose(abierta_2_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *abierta_2_2500 = fopen("abierta_2_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(abierta_2_2500, "%f ", T[i][j]);
				}
				fprintf(abierta_2_2500, "\n");
			}
			fclose(abierta_2_2500);
		}
	}
	fclose(abierta_2_promedio);

	/*Condiciones de frontera periodicas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *periodica_2_0 = fopen("periodica_2_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(periodica_2_0, "%f ", T[i][j]);
		}
		fprintf(periodica_2_0, "\n");
	}
	fclose(periodica_2_0);

	FILE *periodica_2_promedio = fopen("periodica_2_promedio.txt", "w");
	promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(periodica_2_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				if(!((i>=20) && (i<40) && (j>=40) && (j<60)))
				{
					T[i][j] = T_pasado[i][j] + r*(T_pasado[i][mod(j+1, 100)] + T_pasado[i][mod(j-1,100)] + T_pasado[mod(i+1,100)][j] + T_pasado[mod(i-1,100)][j] - 4*T_pasado[i][j]);
				}
				promedio += T[i][j];
			}
		}
		
		promedio = promedio/(100*100);
		fprintf(periodica_2_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *periodica_2_100 = fopen("periodica_2_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(periodica_2_100, "%f ", T[i][j]);
				}
				fprintf(periodica_2_100, "\n");
			}
			fclose(periodica_2_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *periodica_2_2500 = fopen("periodica_2_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(periodica_2_2500, "%f ", T[i][j]);
				}
				fprintf(periodica_2_2500, "\n");
			}
			fclose(periodica_2_2500);
		}
	}
	fclose(periodica_2_promedio);

	/*Condiciones de frontera fijas*/

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if((i>=20) && (i<40) && (j>=40) && (j<60))
			{
				T[i][j] = 100;
			}
			else
			{
				T[i][j] = 50;
			}
		}
	}

	FILE *fija_2_0 = fopen("fija_2_0.txt", "w");
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			fprintf(fija_2_0, "%f ", T[i][j]);
		}
		fprintf(fija_1_0, "\n");
	}
	fclose(fija_2_0);

	FILE *fija_2_promedio = fopen("fija_2_promedio.txt", "w");
	promedio = 0;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			promedio += T[i][j];
		}
	}
	promedio = promedio/(100*100);
	fprintf(fija_2_promedio, "%f %f\n", 0.0, promedio);

	for(n=0;n<2500/dt;n++)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				T_pasado[i][j] = T[i][j];
			}
		}

		for(i=1;i<99;i++)
		{
			for(j=1;j<99;j++)
			{
				if(!((i>=20) && (i<40) && (j>=40) && (j<60)))
				{
					T[i][j] = T_pasado[i][j] + r*(T_pasado[i][j+1] + T_pasado[i][j-1] + T_pasado[i+1][j] + T_pasado[i-1][j] - 4*T_pasado[i][j]);
				}
			}
		}

		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				promedio += T[i][j];
			}
		}
		promedio = promedio/(100*100);
		fprintf(fija_2_promedio, "%f %f\n", ((n+1)*dt), promedio);

		if(n + 1 == 100/dt)
		{
			FILE *fija_2_100 = fopen("fija_2_100.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(fija_2_100, "%f ", T[i][j]);
				}
				fprintf(fija_2_100, "\n");
			}
			fclose(fija_2_100);
		}

		if(n + 1 == 2500/dt)
		{
			FILE *fija_2_2500 = fopen("fija_2_2500.txt", "w");
			for(i=0;i<100;i++)
			{
				for(j=0;j<100;j++)
				{
					fprintf(fija_2_2500, "%f ", T[i][j]);
				}
				fprintf(fija_2_2500, "\n");
			}
			fclose(fija_2_2500);
		}
	}
	fclose(fija_2_promedio);

} 	


int mod (int i, int j)
{	
	int resultado;
	if(j > 0)  
	{ 
		resultado = i % j;
	}
	else
	{
		resultado = i % -j;
	}
	if(resultado < 0)
	{
		resultado += j;
	}
	return resultado;
}
