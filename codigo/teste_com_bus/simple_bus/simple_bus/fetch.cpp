#include "systemc.h"

#ifndef FETCH
    #define FETCH
    #include "fetch.h"
#endif

void fetch_stage::proc(){

    int mydata;
    int cnt = 0;
    unsigned int addr = m_inst_address;


    while(1){
        
        wait(*m_fet_en);
        
        std::cout << sc_time_stamp() << ": fetch_stage\n";
    
        m_bus_port->read(m_unique_priority, &mydata, addr, m_lock);
        
        while ((m_bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK) &&
                                        (m_bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR))
            wait();

        cout << "\nResultado da multiplicacao: " << mydata << endl << endl;



    }

}