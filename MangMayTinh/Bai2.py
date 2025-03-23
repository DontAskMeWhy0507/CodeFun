import socket
import struct

SERVER_IP = "112.137.129.129"
SERVER_PORT = 27002
STUDENT_ID = "23020576"

def send_packet(sock, pkt_type, data):
    pkt = struct.pack("<II", pkt_type, len(data)) + data
    sock.sendall(pkt)

def recv_packet(sock):
    header = sock.recv(8)
    if len(header) < 8:
        return None, None
    pkt_type, data_len = struct.unpack("<II", header)
    data = sock.recv(data_len) if data_len > 0 else b''
    return pkt_type, data

def calculate_polynomial(N, M, x, coefficients):
    result = 0
    for i in range(N + 1):
        result = (result + coefficients[i] * pow(x, i, M)) % M
    return result

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((SERVER_IP, SERVER_PORT))
        print("Connected to server")

        send_packet(sock, 0, STUDENT_ID.encode())
        print(f"Sent PKT_HELLO with student ID: {STUDENT_ID}")

        while True:
            pkt_type, data = recv_packet(sock)
            if pkt_type is None:
                print("Connection closed by server.")
                break
            elif pkt_type == 1:  # PKT_CALC
                N, M, x = struct.unpack("<III", data[:12])
                coefficients = struct.unpack(f"<{N+1}I", data[12:])
                result = calculate_polynomial(N, M, x, coefficients)
                send_packet(sock, 2, struct.pack("<I", result))
                print(f"Sent PKT_RESULT with result: {result}")
            elif pkt_type == 3:  # PKT_BYE
                print("Received PKT_BYE from server. Connection closed.")
                break
            elif pkt_type == 4:  # PKT_FLAG
                flag = data.decode()
                print(f"Received PKT_FLAG with flag: {flag}")
                break

if __name__ == "__main__":
    main()