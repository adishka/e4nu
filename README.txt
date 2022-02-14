git clone https://github.com/afropapp13/e4nu.git e4v_multiplicity
cd e4v_multiplicity
git checkout e4v_multiplicity

# Make sure that your file is structured following the gst genie format 
# https://genie-docdb.pp.rl.ac.uk/DocDB/0000/000002/007/man.pdf (section 9.5.2.1)

# Once that structure is established, change the path to the input gst file in genie_analysis.h (line 346)

make clean;make
./genie_analysis C12 2261 1

# Multiplicity plots of interest for particles within the fiducial volume of the CLAS detector & above detection threshold
# Number of protons: h1_Nprot
# Number of photons: h1_Nphot
# Number of charged pions & photons (radiative and non radiative): h1_Npiphot
# Number of charged pions & photons (non radiative): h1_Npiphot_norad
# Number of charged pions: h1_Npi
# Number of pi plus's: h1_Npipl
# Number of pi minus's: h1_Npimi
