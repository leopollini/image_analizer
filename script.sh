if  [ -z "$1" ]; then
    echo "Error: enter a directory"
    exit
fi

make

FILES=$(ls $1/*.jpg)

echo "Do also Log transform?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) LOGT=$(apis/Log_transformer $FILES) ; mkdir -p $1"_log_transformed"; mv -f $LOGT $1"_log_transformed"/; break ;;
        No ) echo Ok; break;;
    esac
done

#if  [ -z "$2" ]; then
    echo "Using default thresholds: 15, 25, 40"
    #echo 15, 25, 40 > areas_perc.csv
    apis/Pixel_counter 15 $FILES >> areas_perc.csv
    apis/Pixel_counter 25 $FILES >> areas_perc.csv
    apis/Pixel_counter 40 $FILES >> areas_perc.csv
#fi
