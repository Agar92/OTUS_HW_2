set -eu

#pwd
#exit 0

FILE="ip_filter"
#DATAFILE="../OTUS_HW2/ip_filter.tsv"
DATAFILE="$1"
echo "DATAFILE=${DATAFILE}"
OUTPUTFILE="output.dat"
EXPECTED_RESULT="24e7a7b2270daee89c64d3ca5fb3da1a  output.dat"
if [ -f $FILE ]; then
    echo "File found!"
    if [ -f $DATAFILE ]; then
      echo "$DATAFILE found!"
    fi
    ./$FILE $DATAFILE > $OUTPUTFILE
    result=$(md5sum $OUTPUTFILE)
    md5sum --v
    if [ -f $OUTPUTFILE ]; then
      echo "$OUTPUTFILE found!"
    fi
    echo "result=${result}"
    echo "result=${result} EXPECTED_RESULT=${EXPECTED_RESULT}"
#    exit 0
    if [ "$result" = "$EXPECTED_RESULT" ]; then
      echo "Check sums are the same. Good!"
      exit 0
    else
      echo "Check sums are different."
      exit 1
    fi
else
    echo "Binary file not found! Test failed!"
    exit 1
fi

exit 0
