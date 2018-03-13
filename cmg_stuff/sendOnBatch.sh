if [ $# -lt 1 ]
then
  echo "Please provide production name and pass it as first argument: ./sendOnBatch.sh [productionName]"
  echo $#
else 
  source setAAA.sh
  echo "Starting heppy_batch..."
  heppy_batch.py -o /eos/cms/store/group/phys_higgs/pandolf/JetStudiesECAL/10X/$1 run_jetStudiesECAL_cfg.py -b 'bsub -q 8nh -o std_output.txt -J prodMT2test < ./batchScript.sh'
  #heppy_batch.py -o /eos/cms/store/user/pandolf/JetStudiesECAL/10X/$1 run_jetStudiesECAL_cfg.py -b 'bsub -q 8nh -o std_output.txt -J prodMT2test < ./batchScript.sh'
fi
