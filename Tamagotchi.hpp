class Tamagotchi {
public:
    enum State {
        EGG,
        CHILD,
        ADULT,
        // ...
    };

    Tamagotchi();
    void update();
    void feed();
    void play();
    void clean();

private:
    State state;
    int hunger;
    int happiness;
    int health;
    // ...
};
