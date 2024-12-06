#!/bin/bash

# Establecemos que el código de retorno de un pipeline sea el del último programa con código de retorno
# distinto de cero, o cero si todos devuelven cero.
set -o pipefail

LLINDAR_POT=${1:--16}
LLINDAR_R1=${1:-0.3}
LLINDAR_RMAX=${1:-0.46}

# Put here the program (maybe with path)
GETF0="get_pitch --llindar-pot $LLINDAR_POT --llindar-r1 $LLINDAR_R1 --llindar-rmax $LLINDAR_RMAX"

for fwav in pitch_db/train/*.wav; do
    ff0=${fwav/.wav/.f0}
    echo "$GETF0 $fwav $ff0 ----"
	$GETF0 $fwav $ff0 > /dev/null || { echo -e "\nError in $GETF0 $fwav $ff0" && exit 1; }
done

pitch_evaluate pitch_db/train/*.f0ref

exit 0
