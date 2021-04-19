package main

import "testing"

func aTestMailing(t *testing.T) {
	err := SendEmail("root@recolic.net", "testing", "content\nhello")
	if err != nil {
		t.Error(err.Error())
	}
}
