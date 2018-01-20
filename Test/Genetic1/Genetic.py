class Decision(object):

    __init__(self, past_decision, value, score):
        self.past_decision = past_decision
        self.value = value
        self.score = score

class Entity(object):

    __init__(self, hp, atk, defe):
        self.hp = hp
        self.atk = atk
        self.defe = defe


def main():
    game_loop()

def game_loop():
    done = False
    player = new Entity(20, 10, 10)
    enemy = new Entity(15, 7, 7)
    while not done:
        input()

if __name__ == '__main__':
    main()