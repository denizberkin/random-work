import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import datetime


def read_credentials_from_file(path):
    with open(path, "r") as f:
        lines = f.readlines()[0]
        creds = dict()
        for line in lines.split(","):
            k, v = line.split(":")
            creds[k] = v
        return creds


def send_mail(tx, rx, subject="", message="", path=""):
    fromaddr = tx["mail"]
    toaddr = rx
    msg = MIMEMultipart()

    msg['From'] = fromaddr
    msg['To'] = toaddr
    msg['Subject'] = subject

    body = message

    msg.attach(MIMEText(body, 'plain'))

    attachment = open(path, "rb")

    part = MIMEBase('application', 'octate-stream')
    part.set_payload(attachment.read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment", filename=path)

    msg.attach(part)

    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(fromaddr, tx["password"])
    text = msg.as_string()
    server.sendmail(fromaddr, toaddr, text)
    server.quit()


if __name__ == '__main__':
    try:
        creds = read_credentials_from_file("creds.txt")
        send_mail(creds, "berkindeniz2000@gmail.com", "topic here!", "content here!!!\nnew line etc.",
                  "test.pdf")
        print("--------------- !!! Mairu sent !!! ----------------")
    except Exception as e:
        print("excepted!", e.args)
