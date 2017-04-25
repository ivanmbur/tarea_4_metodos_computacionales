GRAFICAS = 1_promedio.pdf 2_promedio.pdf abierta_1_0.pdf abierta_1_100.pdf abierta_1_2500.pdf abierta_2_0.pdf abierta_2_100.pdf abierta_2_2500.pdf fija_1_0.pdf fija_1_100.pdf fija_1_2500.pdf fija_2_0.pdf fija_2_100.pdf fija_2_2500.pdf periodica_1_0.pdf periodica_1_100.pdf periodica_1_2500.pdf periodica_2_0.pdf periodica_2_100.pdf periodica_2_2500.pdf

RESULTADOS = abierta_1_promedio.txt abierta_1_0.txt abierta_1_100.txt abierta_1_2500.txt abierta_2_promedio.txt abierta_2_0.txt abierta_2_100.txt abierta_2_2500.txt fija_1_promedio.txt fija_1_0.txt fija_1_100.txt fija_1_2500.txt fija_2_promedio.txt fija_2_0.txt fija_2_100.txt fija_2_2500.txt periodica_1_promedio.txt periodica_1_0.txt periodica_1_100.txt periodica_1_2500.txt periodica_2_promedio.txt periodica_2_0.txt periodica_2_100.txt periodica_2_2500.txt

Resultados_hw4.pdf : Resultados_hw4.tex $(GRAFICAS)
	pdflatex $<

$(GRAFICAS) : Plots_Temperatura.py $(RESULTADOS)
	python $<

$(RESULTADOS) : DifusionTemperatura.x
	./$<

DifusionTemperatura.x : DifusionTemperatura.c
	cc $< -lm -o $@
