# Solaris on sparc
# Dual processor
#MAKEJOBFLAGS = -j 2
TARGETOS = sparc-sun-solaris
HOSTOS = sparc-sun-solaris

TARGETCXXFLAGS = "-O2 -I$(HOME)/local-$(HOSTNAME)/include"