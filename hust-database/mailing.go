package main

import (
	"crypto/tls"
	"fmt"
	"net"
	"net/mail"
	"net/smtp"
)

func SendEmail(toAddress, subj, body string) error {
	// This address&password can be public. Nothing important in it.
	username := "no-reply-hust@recolic.net"
	password := "fuckinghust"

	from := mail.Address{Name: "", Address: username}
	to := mail.Address{Name: "", Address: toAddress}

	// Setup headers
	headers := make(map[string]string)
	headers["From"] = from.String()
	headers["To"] = to.String()
	headers["Subject"] = subj

	// Setup message
	message := ""
	for k, v := range headers {
		message += fmt.Sprintf("%s: %s\r\n", k, v)
	}
	message += "\r\n" + body

	// Connect to the SMTP Server
	servername := "smtp.recolic.net:587"

	host, _, _ := net.SplitHostPort(servername)

	auth := smtp.PlainAuth("", username, password, host)

	// TLS config
	tlsconfig := &tls.Config{
		InsecureSkipVerify: true,
		ServerName:         host,
	}

	c, err := smtp.Dial(servername)
	if err != nil {
		return err
	}

	c.StartTLS(tlsconfig)

	// Auth
	if err = c.Auth(auth); err != nil {
		return err
	}

	// To && From
	if err = c.Mail(from.Address); err != nil {
		return err
	}

	if err = c.Rcpt(to.Address); err != nil {
		return err
	}

	// Data
	w, err := c.Data()
	if err != nil {
		return err
	}

	_, err = w.Write([]byte(message))
	if err != nil {
		return err
	}

	err = w.Close()
	if err != nil {
		return err
	}

	c.Quit()
	return nil
}
