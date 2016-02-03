import itertools as it

numbers = [23, 20, 44, 32, 7, 12]
letters = ['a', 'b', 'c', 'd', 'e', 'f']
booleans = [1, 0, 1, 0, 0, 1]
decimals = [0.1, 0.7, 0.4, 0.4, 0.5]

print list(it.chain(numbers, decimals, letters))

for i in it.count(10, 0.25):
    if i < 20 and (i % 2):
        print i
    else:
        break


def join(a, b):
    return "{}-{}".format(a, b)


print list(it.ifilter(lambda x: x % 2, numbers))
print list(it.compress(decimals, booleans))
print list(it.imap(None, numbers, letters))
print list(it.imap(join, numbers, letters))
