INDIGO_LIB = ../indigo_libs
INDIGO_LIB = .
i_client: i_client.cc
	g++ -O3 -Wall -shared -std=c++11 -fpermissive -fPIC -I${INDIGO_LIB} `python3 -m pybind11 --includes` i_client.cc -o i_client`python3-config --extension-suffix`
