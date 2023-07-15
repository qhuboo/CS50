from cs50 import get_string


def main():
    while True:
        number = get_string("Number: ")
        if number.isnumeric():
            break
    if(luhn(number)):
        length_type(number)
    else:
        print("INVALID")


def luhn(number):
    cur_sum = 0
    r_number = number[::-1]
    for i in range(len(number)):
        if i % 2 == 0:
            cur_sum += int(r_number[i])
        else:
            tmp = int(r_number[i]) * 2
            cur_sum += tmp // 10
            cur_sum += tmp % 10

    if cur_sum % 10 == 0:
        return True
    else:
        return False


def length_type(number):
    if (len(number) == 13 or len(number) == 16) and number[0] == '4':
        print("VISA")
    elif len(number) == 16 and number[0] == '5' and (int(number[1]) in range(1,6)):
        print("MASTERCARD")
    elif len(number) == 15 and number[0] == '3' and (number[1] == '4' or number[1] == '7'):
        print("AMEX")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
