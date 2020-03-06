// Pointers to singleton altimeter instance
Altimeter* altimeter;
Orientation* orientation;

// Circular Buffers to keep track of last 10 data points
CircularBuffer<float, 10> altitudeBuffer;
CircularBuffer<float, 10> verticalVelocityBuffer;
CircularBuffer<float, 10> verticalAccelerationBuffer;

void UpdateBuffers();
bool DetectLaunch();
