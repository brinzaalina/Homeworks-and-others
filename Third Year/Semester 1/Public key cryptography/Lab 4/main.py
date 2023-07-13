import random


def binary_decomposition(k):
    # returns the representation of the number k written as sum of powers of 2
    # ex: 13 = 2^3 + 2^2 + 2^0 = 1101
    # returns [0, 2, 3]
    v = []
    binary = []
    while k > 0:
        v.append(k % 2)
        k = k // 2
    for i in range(0, len(v)):
        if v[i] == 1:
            binary.append(i)
    return binary


def compute_modular_squaring(a, k, n):
    # returns a^k mod n, using modular squaring exponentiation
    sum = binary_decomposition(k)
    rests = []
    stop = sum[-1]
    aux = a % n
    for i in range(0, stop + 1):
        if i in sum:
            rests.append(aux)
        aux = (aux * aux) % n
    result = 1
    for i in rests:
        result = (result * i) % n
    return result


def decompose_n(n):
    # represent n as 2^s * t and return s and t
    p = 0
    while n % 2 == 0:
        n = n // 2
        p += 1
    return p, n


def get_first_one(a_seq):
    # return the index of the first appearance of 1 in the sequence
    for i in range(1, len(a_seq)):
        if a_seq[i] == 1:
            return i
    return 0


def miller_rabin_test(n, k):
    # Miller Rabin primality test
    # it can have two results: false - the given number is composite, true - the given number is probably prime
    composite = False
    j = 0
    while j < k and not composite:
        aux = n - 1
        # decompose n - 1 as 2^s * t
        (s, t) = decompose_n(aux)
        # generate a random number between 1 and n
        a = random.randint(1, n)
        a_seq = []
        p = 1
        # compute the sequence (mod n): a^t, a^(2t), a^(4t), ..., a^(2^s * t)
        for i in range(s + 1):
            a_seq.append(compute_modular_squaring(a, p * t, n))
            p = p * 2
        index = get_first_one(a_seq)
        # if the first element of the sequence is 1
        # or if there is an element of the sequence that is 1 and its predecessor is -1 (n-1)
        # the process continues
        if a_seq[0] == 1 or (index > 0 and a_seq[index - 1] == n - 1):
            composite = False
        else:
            # otherwise, the number is composite
            composite = True
        j += 1
    return not composite


def generate_prime_number():
    # generate a random large prime number
    # check the primality of the number using the Miller Rabin test
    nr = random.randint(1000, 18000)
    i = 1
    k = 5
    while nr % 2 == 0 or not miller_rabin_test(nr, k):
        nr = random.randint(1000 + i, 18000)
        i += 1
    return nr


def create_and_check_generator_sequence(g, p):
    # compute the sequence (mod p): g^1, g^2, g^3, ..., g^(p-1)
    # until we get an element that is already in the sequence
    # if the length of the sequence is p-1, we have a generator
    seq = [g]
    aux = g
    stop = False
    while not stop:
        aux = (aux * g) % p
        if aux in seq:
            stop = True
        else:
            seq.append(aux)
    if len(seq) == p - 1:
        return True
    return False


def get_generator(p):
    # generate a generator for the given prime number
    # the generator must be a number between 1 and p-1
    # we have to compute the sequence (mod p): g^1, g^2, g^3, ..., g^(p-1)
    # we keep generating a random number until we get a generator of the sequence
    g = random.randint(2, p)
    while not create_and_check_generator_sequence(g, p):
        g = random.randint(2, p)
    return g


def key_generation():
    # generate the public and private keys
    # generate a large prime number
    p = generate_prime_number()

    # generate a generator for the prime number
    g = get_generator(p)
    # generate a random number between 1 and p-1 which is the private key
    a = random.randint(1, p - 2)

    # compute the public key which is (g, a, g^a mod p)
    k = compute_modular_squaring(g, a, p)
    return p, g, k, a


def validate_plaintext_and_cyphertext(plaintext):
    # check if every character in the plaintext is a letter from our alphabet
    characters = [' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                  't', 'u', 'v', 'w', 'x', 'y', 'z']
    elems = list(plaintext)
    for e in elems:
        if e not in characters:
            return False
    return True


def calculate_numerical_equiv(word, size_of_block=3):
    # calculate the numerical equivalent of a word
    # the word is split into blocks of size 3
    # each block is converted into a number
    # the given word is converted into a sequence of numbers
    letters = list(word)
    characters = [' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                  't', 'u', 'v', 'w', 'x', 'y', 'z']
    dict = {}
    for i in range(0, len(characters)):
        dict[characters[i]] = i

    j = 0
    nr_equiv = []
    while j < len(letters):
        i = j
        aux = 0
        while i < len(letters) and i < j + size_of_block:
            i += 1
        i -= j
        for a in range(0, i):
            aux += pow(27, size_of_block - a - 1) * dict[letters[j + a]]
        j += i
        nr_equiv.append(aux)
    return nr_equiv


def get_equiv_letters(m, size_of_block=3):
    # calculate the letters that correspond to the given number
    # the number is represented as a sum of powers of 27 and the letters are calculated accordingly
    characters = [' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                  't', 'u', 'v', 'w', 'x', 'y', 'z']
    l_dict = {}
    for i in range(0, len(characters)):
        l_dict[characters[i]] = i
    letters = ""
    size_of_block -= 1
    while m > 0 or size_of_block >= 0:
        letters += characters[m // pow(27, size_of_block)]
        m = m % pow(27, size_of_block)
        size_of_block -= 1
    return letters


def encryption(p, g, k, m):
    # the encryption function takes as input the public key (p, g, g^a) and the plaintext m
    # g^a is k
    # generate a random number between 1 and p-1
    k1 = random.randint(1, p - 2)
    # compute alpha and beta where:
    # alpha = g^k1 mod p
    # beta = m * (g^a)^k1 mod p
    alpha = compute_modular_squaring(g, k1, p)
    aux = compute_modular_squaring(k, k1, p)
    beta = (m * aux) % p
    # returns the tuple (alpha, beta) which is the ciphertext
    return alpha, beta


def decryption(alpha, beta, a, p):
    # the decryption function takes as input the private key a, the ciphertext (alpha, beta) and the prime number p
    aux = compute_modular_squaring(alpha, p - 1 - a, p)
    # compute the plaintext m = beta * alpha^(-a) mod p
    return (beta * aux) % p


def el_gamal(message):
    # generate the public and private keys
    p, g, k, a = key_generation()
    # choose the length of the plaintext blocks (k) and the ciphertext blocks (l)
    # the condition that must be satisfied is: 27^k < p < 27^l
    k_size = 3
    l_size = 4
    # if the plaintext is not valid, we return an error message
    if not validate_plaintext_and_cyphertext(message):
        print("Invalid message")
        return None
    else:
        print("Plain text: ", message)

    # calculate the numerical equivalent of the plaintext
    nr = calculate_numerical_equiv(message, k_size)
    cipher = ""
    # for each block of the plaintext, we encrypt it
    for i in nr:
        # get the ciphertext (alpha, beta) for the current block
        alpha, beta = encryption(p, g, k, i)
        # get the letters that correspond to the numbers alpha and beta
        al = get_equiv_letters(alpha, l_size)
        be = get_equiv_letters(beta, l_size)
        # add the ciphertext letters to the message
        cipher += al + be
    # if the ciphertext is valid, we print it and proceed to decryption
    if validate_plaintext_and_cyphertext(cipher):
        print("Cipher text: ", cipher)
    # compute the numerical equivalent of the ciphertext
    nr1 = calculate_numerical_equiv(cipher, l_size)
    i = 0
    final_message = ""
    # each block of the ciphertext is decrypted and
    # the letters that correspond to the numbers are added to the final message
    while i < len(nr1) - 1:
        m = decryption(nr1[i], nr1[i + 1], a, p)
        final_message += get_equiv_letters(m, k_size)
        i += 2
    # print the final message
    print("Final text: ", final_message)
    return final_message


def main():
    message = input("Enter the message: ")
    el_gamal(message)


if __name__ == '__main__':
    main()