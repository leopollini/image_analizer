if  [ -z "$1" ]; then
    echo "Error: enter a directory"
    exit
fi

make

CROP=$(apis/Cropper $(ls $1/*.jpg))

echo "Do also Log transform?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) LOGT=$(apis/Log_transformer $CROP) ; mkdir -p $1"_log_transformed"; mv -f $LOGT $1"_log_transformed"/; break ;;
        No ) echo Ok; break;;
    esac
done

#if  [ -z "$2" ]; then
    echo "Using default thresholds: 15, 25, 40"
    #echo 15, 25, 40 > areas_perc.csv
    apis/Pixel_counter 15 $CROP >> areas_perc.csv
    apis/Pixel_counter 25 $CROP >> areas_perc.csv
    apis/Pixel_counter 40 $CROP >> areas_perc.csv
#fi


mkdir -p $1_cropped
mv -f $CROP $1_cropped
