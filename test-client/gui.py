import tkinter as tk
from tkinter import ttk
from client import Client
import threading


ROWLEN = 3
COLSPAN = 3


def new_thread(target, daemon=True, args=()):
    thread = threading.Thread(target=target, args=args, daemon=daemon)
    thread.start()


class Gui(tk.Tk):
    def __init__(self):
        super().__init__()
        self.resizable(False, False)

        self.client = Client(self)
        self.widgets = []
        self.title("Farkle commands")

        self.text_ = tk.Text(self, height=5, width=52, state="disable")
        self.input_ = tk.Label(self)
        self.commands_ = ttk.Combobox(self, values=[], state="readonly")

        # Output
        tk.Label(self, text="Output").grid(columnspan=COLSPAN)
        self.text_.grid(columnspan=COLSPAN)

        # Input
        tk.Label(self, text="Input").grid(columnspan=COLSPAN)
        tk.Entry(self).grid(columnspan=COLSPAN)

        # Send
        tk.Button(self, text="Send", command=lambda: self.send_event(None)).grid(columnspan=COLSPAN)

        # Close
        tk.Button(self, text="Close", command=self.destroy).grid(columnspan=COLSPAN)

        # Binds
        self.bind('<Return>', self.send_event)
        self.commands_.bind("<<ComboboxSelected>>", None)

        self.after(0, new_thread(target=self.client.receive))
        self.client.send(bytes("TEST", encoding="UTF-8"))

    def send_event(self, _):
        msg = self.input_["text"]
        self.client.send(bytes(msg, encoding="UTF-8"))

    def receive_event(self, msg):
        self.text_.config(state="normal")
        self.text_.insert('end', msg+"\n")
        self.text_.see('end')
        self.text_.config(state="disable")


if __name__ == '__main__':
    gui = Gui()
    gui.mainloop()
