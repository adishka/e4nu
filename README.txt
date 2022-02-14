git clone https://github.com/afropapp13/e4nu.git e4v_truth
cd e4v_truth
git checkout e4v_truth

# Make sure that your file is structured following the gst genie format 
# https://genie-docdb.pp.rl.ac.uk/DocDB/0000/000002/007/man.pdf (section 9.5.2.1)

# Once that structure is established, change the path to the input gst file in genie_analysis.h (line 350)

make clean;make
./genie_analysis C12 2261 1


