ndndump - packet capture and analysis tool for NDN
==================================================

ndndump was created to provide a tcpdump-like tool for Named Data Networking (NDN).
Initial project available at [github](https://github.com/zhenkai/ndndump/)
For more information about NDN, refer to [NDN Project homepage](http://www.named-data.net/).

This fork introduce CSV output capabilities for an output more adapted to data analysis 

## Usage example

	sudo ./build/ndndump -s , -o dump.csv -v -i lo
	
This command generate a commas separated csv file with headers called dump.csv

	sudo ./build/ndndump -v -i lo
	
This command generate a space separated output on the console

## CSV fields

in general all the packets have the same output. However, some fields are not applicable for Data or Interests packets
Note that the fields that does not apply to a type of packet will be empty.

### General fields description

	Timestamp,Source,Destination,TunnelType,Name,FreshnessPeriod,MustBeFresh,Nonce,InterestLifetime

#### Interest Packet fields description

	Timestamp,Source,Destination,TunnelType,Name,n/a,MustBeFresh,Nonce,InterestLifetime

For more information about NDN TLV, refer to [NDN Interest Packet](http://named-data.net/doc/ndn-tlv/interest.html)


#### Data Packet fields description

	Timestamp,Source,Destination,TunnelType,Name,FreshnessPeriod,n/a,n/a,n/a

For more information about NDN TLV, refer to [NDN Data Packet](http://named-data.net/doc/ndn-tlv/data.html)

## Output examples

Timestamp,Source,Destination,TunnelType,Name,FreshnessPeriod,MustBeFresh,Nonce,InterestLifetime
1472017257.068399,127.0.0.1,127.0.0.1,UDP,48,INTEREST,/example/testApp/randomData,,1,2817859521,1000
1472017257.073000,127.0.0.1,127.0.0.1,UDP,398,DATA,/example/testApp/randomData/testApp/%FD%00%00%01V%BB%10%D2n,10000,,,


## Prerequisites

- ndn-cxx library (https://github.com/named-data/ndn-cxx)

    For detailed installation instructions refer to
    [ndn-cxx getting started instructions](https://github.com/named-data/ndn-cxx)

## Source installation

The following commands will configure, build, and install ndndump:

    ./waf configure
    ./waf
    sudo ./waf install

## Command line options

    Usage:
      ./build/ndndump  [-s separator] [-o output-csv-file] [-i interface] [-f name-filter] [tcpdump-expression]

    Default tcpdump-expression:
      '(ether proto 0x8624) || (tcp port 6363) || (udp port 6363)'

      -h [ --help ]          Produce this help message
      -i [ --interface ] arg Interface from which to dump packets
      -r [ --read ] arg      Read  packets  from file
      -v [ --verbose ]       When  parsing  and  printing, produce verbose output
      -f [ --filter ] arg    Regular expression to filter out Interest and Data
                             packets
      -s [ --separator ] arg Separator between fields used for the output 
      -f [ --filter ] arg    File to be used as output for the CSV format


