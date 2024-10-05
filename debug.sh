graphNumRow=5
graphNumColumn=5
graphDegree=4
graphMaxLength=2
maxGeneration=200
population=10
indivMutateProbability=0.01
geneMutateProbability=0.01
generationChangeModel="dmsxf"
seed=42

gdb --args ./grid \
    -r $graphNumRow \
    -c $graphNumColumn \
    -d $graphDegree \
    -l $graphMaxLength \
    -p $population \
    -g $maxGeneration \
    -m $generationChangeModel \
    -im $indivMutateProbability \
    -gm $geneMutateProbability \
    -seed $seed;