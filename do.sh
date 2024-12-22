graphNumRow=10
graphNumColumn=10
graphDegree=4
graphMaxLength=2
maxGeneration=1000
population=200
indivMutateProbability=0.05
geneMutateProbability=0.05
generationChangeModel="dmsxf"
seed=42

./grid \
    -r $graphNumRow \
    -c $graphNumColumn \
    -d $graphDegree \
    -l $graphMaxLength \
    -p $population \
    -g $maxGeneration \
    -m $generationChangeModel \
    -im $indivMutateProbability \
    -gm $geneMutateProbability \
    -seed $seed \
    -f "debug"