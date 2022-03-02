# e4v Signal definition

1) Min Q2 threshold
	a) Q2 > 0.1 GeV^2/c^2 @ 1.1 GeV
	b) Q2 > 0.4 GeV^2/c^2 @ 2.2 GeV	
	a) Q2 > 0.8 GeV^2/c^2 @ 4.4 GeV

2) Min outgoing electron momentum
	a) Pe > 0.40 GeV/c @ 1.1 GeV
	b) Pe > 0.55 GeV/c @ 2.2 GeV
	c) Pe > 1.10 GeV/c @ 4.4 GeV
	
3) Min electron angle
	a) theta_e > 17 + 7 / Pe @ 1.1 GeV [deg]
	b) theta_e > 16 + 10.5 / Pe @ 2.2 GeV [deg]
	c) theta_e > 13.5 + 15 / Pe @ 1.1 GeV [deg]		

4) Invariant mass W < 2 GeV^{2}/c^{2}

5) 1 proton above threshold Pp > 0.3 GeV/c & theta_p > 12 deg

6) 0 charged pions above threshold Ppi > 0.15 GeV/c

7) Min pi+ angle > 12 deg

8) Min pi- angle
	a) theta_pi- > 17 + 4 / Ppi- @ 1.1 GeV [deg]
	b) theta_pi- > 25 + 7 / Ppi- @ 2.2/4.4 GeV [deg] for Ppi- < 0.35 GeV/c
	   theta_pi- > 16 + 10 / Ppi- @ 2.2/4.4 GeV [deg] for Ppi- > 0.35 GeV/c


9) 0 photons above threshold Pgamma > 0.3 GeV/c 

##############################################################################################

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


# Extended Data Figure 3 / Multiplicities: The simulation part is normalized in such a way, so that
#	a) for protons, the multiplicity = 1 bin is the same for data/MC
	b) for charged pions, the multiplicity = 0 bin is the same for data/MC
	  
