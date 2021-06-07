unsigned int sleep(unsigned int seconds) {
    int i;
    long calculatedLoop = seconds * 1000000000;
    for (i = 0; i < calculatedLoop; i++) {
        ;
    }
    return 0;
};