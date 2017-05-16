
#include <yarp/os/Network.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Property.h>
#include <yarp/os/Random.h>
#include <yarp/os/Time.h>

using namespace std;
using namespace yarp::os;

int produce_sync() {
    Port outPort;
    // open the output port
     
    if (!outPort.open("/producer/out")) {
        yError() << "cannot open the output port";
        return -1;
    }

    while(true) {        
        Bottle data;
        // add a random value using Random::uniform(1,100) to the bottle
        data.addInt(Random::uniform(1,100));

        // write to the port
        yInfo()<< "writing data ...";
		outPort.write(data); 

        // delay for 100ms
        Time::delay(0.1);
    }
    return 0;
}

int produce_async() {
    BufferedPort<Bottle> outPort;
    // open the output buffered port
    
    if (!outPort.open("/producer/out")) {
        yError() << "cannot open the output port";
        return -1;
    }

	
	
    while(true) {
		
		
        // add a random value using Random::uniform(1,100) to a bottle
        Bottle& datas = outPort.prepare();
		datas.addInt(Random::uniform(1,100));
		

        // write to the port
        yInfo()<< "writing data ...";
        outPort.write();

        // delay for 100ms
        Time::delay(0.1);
    }

    return 0;
}


int main(int argc, char *argv[]) {
    Network yarp;

    Property prop;
    prop.fromCommand(argc, argv);
    if(prop.check("async")) {
        yInfo()<<"Producer using async mode";
        return produce_async();
    }

    yInfo()<<"Producer using sync mode";
    return produce_sync();
}
