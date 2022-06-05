from vidstream import StreamingServer
import threading

receiver = StreamingServer('192.168.1.104', 9999, slots=8, quit_key='q')

t = threading.Thread(target=receiver.start_server)

t.start()

while input() != 'stop':
    continue

receiver.stop_server()
