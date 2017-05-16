#include <yarp/os/Network.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Port.h>
#include <yarp/os/Property.h>
#include <yarp/os/Time.h>

using namespace std;
using namespace yarp::os;

int main(int argc, char *argv[]) {
    Network yarp;    

    Property prop;
    prop.fromCommand(argc, argv);
    double delay = 0.0;
    if(prop.check("delay")) {
        delay = prop.find("delay").asDouble();
        yInfo()<<"Consumer delays reading by"<<delay<<"seconds.";
    }


    Port inPort, outPort;
    // open "/consumer/in" and  "/consumer/out" ports
	
	if (!inPort.open("/consumer/in")) { 
        yError() << "cannot open the input port";
        return -1;
    }
	
	
    if (!outPort.open("/consumer/out")) {
        yError() << "cannot open the output port";
        return -1;
    }

     
	
    while (true) {
		
		
        Bottle data;
        // read the data from the port and measure the rate (time delay)
        // use yarp::os::Time::now() for measuring the time
         if(!inPort.read(data)) {  
            yError()<<"error while reading";
            return 0;
        }

        // print out the data
        printf("Bottle data is: %s\n", data.toString().c_str());
        double t1 = Time::now();
		
        // write measured rate to the output port
		 yInfo()<< "writing data ...";
		 outPort.write(data);

        // delay the reading
        Time::delay(delay);
		
		double t2 = Time::now();
		printf("acquired %f seconds\n", t2-t1);
		
    }
    return 0;
}
