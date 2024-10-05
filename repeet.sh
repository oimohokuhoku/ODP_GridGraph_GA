graphNumRow=10
graphNumColumn=10
graphDegree=4
graphMaxLength=2
maxGeneration=1000
population=100
indivMutateProbability=0.05
geneMutateProbability=0.05
generationChangeModel="dmsxf"

beginSeed=0
endSeed=5

for ((i=$beginSeed; i < endSeed; i=i+1)); 
    do ./grid \
        -r $graphNumRow \
        -c $graphNumColumn \
        -d $graphDegree \
        -l $graphMaxLength \
        -p $population \
        -g $maxGeneration \
        -m $generationChangeModel \
        -im $indivMutateProbability \
        -gm $geneMutateProbability \
        -seed $i;
done