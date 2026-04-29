#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

const int AMEX_LEN = 15;
const int MC_LEN = 16;
const int VISA_LEN1 = 13;
const int VISA_LEN2 = 16;

// enum to hold possible card types
typedef enum Card {
  AMEX,
  MASTERCARD,
  VISA,
  INVALID,
} Card;

// simple check if the first 2 digits are 34 or 37
// matching an AMEX card
bool is_amex(int lead_digits, int len) {
  if (len != AMEX_LEN) {
    return false;
  }
  switch (lead_digits) {
  case 34:
    return true;
  case 37:
    return true;
  }
  return false;
}
// simple check if the first 2 digits are 51, 52, 53, 54 or 55
// matching a MASTERCARD
bool is_mastercard(int lead_digits, int len) {
  if (len != MC_LEN) {
    return false;
  }
  if (lead_digits >= 51 && lead_digits <= 55) {
    return true;
  }
  return false;
}

// this only needed to check the very first digit this works too
// checking that the first digit is 4
// matching a VISA
bool is_visa(int lead_digits, int len) {
  if (len != VISA_LEN1 && len != VISA_LEN2) {
    return false;
  }
  if (lead_digits >= 40 && lead_digits <= 49) {
    return true;
  }
  return false;
}

int card_length(long cc) {
  int length = 0;
  while (cc != 0) {
    length++;
    cc /= 10;
  }
  return length;
}

// returns an enum from Card after checking it against card patterns
Card card_type(long cc, int len) {
  // this is important to stop stripping off last numbers when the number hits 2
  // digits
  while (cc >= 100) {
    cc /= 10;
  }
  // simple series of if else if to check against card patterns
  if (is_amex(cc, len)) {
    return AMEX;
  } else if (is_mastercard(cc, len)) {
    return MASTERCARD;
  } else if (is_visa(cc, len)) {
    return VISA;
  } else {
    return INVALID;
  }
}

// takes credit card number and returns luhn's checksum
int luhn(long cc) {
  int checksum = 0;
  int idx = 0;
  // run until we stripped out all the digits
  while (cc != 0) {
    idx++;
    // get last digit
    long last = cc % 10;
    // if digit idx is even its part of phase 1
    if (idx % 2 == 0) {
      // multiply last number by 2
      int last_doubled = last * 2;
      // now we need that numbers digits so nest the same logic
      while (last_doubled != 0) {
        int last_from_doubled = last_doubled % 10;
        checksum += last_from_doubled;
        last_doubled /= 10;
      }
    } else {
      // else the other numbers as phase 2
      checksum += last;
    }
    cc /= 10;
  }
  return checksum;
}

// simple switch statement to print a card type
void print_card(Card type) {
  switch (type) {
  case AMEX:
    puts("AMEX");
    break;
  case MASTERCARD:
    puts("MASTERCARD");
    break;
  case VISA:
    puts("VISA");
    break;
  case INVALID:
    puts("INVALID");
    break;
  }
}

// Test if a CC number is syntactically correct
int main(void) {
  // get input from the user and store it into cc
  long cc = get_long("Number: ");
  // get cc number length
  int length = card_length(cc);
  // get card type from the cc number and store in type
  int type = card_type(cc, length);
  // get the checksum from the luhn function using cc number
  int checksum = luhn(cc);
  printf("%d", checksum);
  // if checksum is valid print card type
  if (checksum % 10 == 0) {
    print_card(type);
  } else {
    puts("INVALID");
  }
}
