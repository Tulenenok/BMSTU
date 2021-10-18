import random

adresses = ['1 First Street', '2 Second Street', '3 Third Street', '4 Fourth Street',
            '5 Fifth Street', '6 Sixth Street', '7 Seventh Sreet', '8 Eighth Street',
            '9 Nineth Street', '10 Tenth Street']

S = [random.randint(15, 200) for i in range(10)]
count_rooms = [random.randint(1, 5) for i in range(10)]
price = [random.randint(1000, 10000) for i in range(10)]
olds = [random.randint(0, 1) for i in range(10)]
build_times = [random.randint(1850, 2021) for i in range(10)]
owners = [random.randint(1, 20) for i in range(10)]
residents = [random.randint(1, 5) for i in range(10)]
was_animals = [random.randint(0, 1) for i in range(10)]
with_finishing = [random.randint(0, 1) for i in range(10)]


with open('data.txt', 'w') as f:
    for i in range(700):
        c = random.choice(olds)
        w = random.choice(with_finishing)
        b = random.choice(build_times)
        o = random.choice(owners)
        r = random.choice(residents)
        a = random.choice(was_animals)
        f.write(f'{random.choice(adresses)};{random.choice(S)};{random.choice(count_rooms)};{random.choice(price)};{c};' + (f'{w};-;-;-;-\n' if not c else f'-;{b};{o};{r};{a}\n'))
