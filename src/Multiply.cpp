#include "HEAR_math/Multiply.hpp"

Multiply::Multiply(std::function<float(float,float)> t_operation) {
    this->_operation = t_operation;
    this->_v1=0.0;
    this->_v2=0.0;
    this->_input_port_0 = new InputPort(ports_id::IP_0_DATA, this);
    this->_input_port_1 = new InputPort(ports_id::IP_1_DATA, this);
    this->_output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0, _input_port_1, _output_port};
}

Multiply::~Multiply() {

}

void Multiply::runTask(DataMsg* t_msg) {
    FloatMsg float_msg;
    float_msg.data = this->_operation(_v1, _v2);
    this->_output_port->receiveMsgData(&float_msg);
}

void Multiply::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA){
        FloatMsg* float_msg = (FloatMsg*)t_msg;
        float data = float_msg->data;
        _v1 = data;
        this->runTask(t_msg);
    }else if(t_port->getID() == ports_id::IP_1_DATA){ 
        FloatMsg* float_msg = (FloatMsg*)t_msg;
        float data = float_msg->data;
        _v2 = data;
        this->runTask(t_msg);
    }
}