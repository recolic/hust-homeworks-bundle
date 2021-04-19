package main

import "testing"

func TestMoney(t *testing.T) {
	stringAndMoney := map[string]money_t{
		"1.23":    money_t(123),
		"0.01":    money_t(1),
		"1122.33": money_t(112233),
		"0.11":    money_t(11),
		"0.00":    money_t(0),
		"-13.33":  money_t(-1333),
		"-0.01":   money_t(-1),
	}
	mStringAndMoney := map[string]money_t{
		"1.233":    money_t(123),
		"0.01001":    money_t(1),
		"1122.3": money_t(112230),
		"":    money_t(0),
		"0":    money_t(0),
		"-13.3321412":  money_t(-1333),
		"-1":   money_t(-100),
	}

	for str, money := range stringAndMoney {
		if money.String() != str {
			t.Error("money to string boom: " + str + " -- " + money.String())
		}
		rmoney, err := StringToMoneyT(str)
		if err != nil || rmoney != money {
			t.Error("string to money boom: " + str)
		}
	}
	for str, money := range mStringAndMoney {
		rmoney, err := StringToMoneyT(str)
		if err != nil || rmoney != money {
			t.Error("string to money boom: " + str)
		}
	}
}
