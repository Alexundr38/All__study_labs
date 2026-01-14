if __name__ =="__main__":
    pattern = input()
    text = input()
    unq_symb = []
    for i in text:
        if not (i in unq_symb):
            unq_symb.append(i)
    power = len(unq_symb)
    q = 53
    polynomial_value = []
    text_length = len(text)
    pattern_hash = 0
    pattern_length = len(pattern)
    for i in range(pattern_length):
        polynomial_value.append(power ** i)

    for i in range(pattern_length):
        pattern_hash = (pattern_hash + unq_symb.index(pattern[i]) * polynomial_value[pattern_length - i - 1]) % q

    index_data = []
    current_hash = 0
    for i in range(text_length):
        if i < pattern_length:
            current_hash = (current_hash + unq_symb.index(text[i]) * polynomial_value[pattern_length - i - 1]) % q
        else:
            old_hash = (unq_symb.index(text[i - pattern_length]) * polynomial_value[pattern_length - 1]) % q
            current_hash = ((current_hash - old_hash) * power + unq_symb.index(text[i])) % q
        if current_hash == pattern_hash:
            add_value = i - pattern_length + 1
            flag = True
            if i < pattern_length:
                start = 0
            else:
                start = i - pattern_length + 1
            for j in range(start, i + 1):
                if (text[j] != pattern[j - start]):
                    flag = False
                    break
            if flag == True and add_value >= 0:
                index_data.append(add_value)

    print(' '.join(map(str, index_data)))