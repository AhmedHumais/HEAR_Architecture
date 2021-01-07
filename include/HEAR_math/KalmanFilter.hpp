#pragma once

#include "Eigen/Core"
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"
#include "HEAR_msg/Vector3DMsg.hpp"

class KalmanFilter : public Block {
    private:
        Port* _input_port_0;
        Port* _input_port_1;
        Port* _output_port_0;
        Port* _output_port_1;
        float _dt = 0.005;
        float _war_w = 0.55;
        float _R_pos;
        float _pos_val=0;
        Eigen::Matrix<float, 3, 1> _x, _G;
        Eigen::Matrix<float, 3, 3> _P, _F, _Q;
        Eigen::Matrix<float, 1, 3> _H_pos;
        void resetFilter();

    public:
        enum ports_id {IP_0_ACC, IP_1_POS, OP_0_POS, OP_1_VEL};
        void process(DataMsg* t_msg, Port* t_port);
        void setTimeStep(float);
        void doPredictionStep(float);
        void doMeasurementStep(float);
        KalmanFilter(float);
        ~KalmanFilter();
};