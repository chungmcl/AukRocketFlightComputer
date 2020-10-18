// Pointers to singleton module instances
Altimeter* altimeter;
Orientation* orientation;
Radio* radio;

// Circular Buffers to keep track of last 10 data points
CircularBuffer<float, 10> altitudeBuffer;
CircularBuffer<float, 10> verticalVelocityBuffer;
CircularBuffer<float, 10> verticalAccelerationBuffer;



void UpdateBuffers();
bool DetectLaunch();
