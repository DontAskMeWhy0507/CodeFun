import socket
import struct

SERVER_IP = "112.137.129.129"
SERVER_PORT = 27001
STUDENT_ID = "23020576"  # Thay bằng mã sinh viên của bạn

def send_packet(sock, pkt_type, data):
    """Gửi gói tin với type và data đã cho."""
    pkt = struct.pack("<II", pkt_type, len(data)) + data
    sock.sendall(pkt)

def recv_packet(sock):
    """Nhận một gói tin từ server."""
    header = sock.recv(8)
    if len(header) < 8:
        return None, None
    pkt_type, data_len = struct.unpack("<II", header)
    data = sock.recv(data_len) if data_len > 0 else b''
    return pkt_type, data

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((SERVER_IP, SERVER_PORT))
        print("Connected to server")

        # 1. Gửi gói PKT_HELLO
        send_packet(sock, 0, STUDENT_ID.encode())
        print(f"Sent PKT_HELLO with student ID: {STUDENT_ID}")

        while True:
            # 2. Nhận gói tin từ server
            pkt_type, data = recv_packet(sock)
            if pkt_type is None:
                print("Connection closed by server.")
                break

            if pkt_type == 1:  # PKT_CALC
                a, b = struct.unpack("<II", data)
                print(f"Received PKT_CALC: a={a}, b={b}")
                result = (a + b) % (2**32)  # Đảm bảo trong phạm vi 32-bit
                send_packet(sock, 2, struct.pack("<I", result))
                print(f"Sent PKT_RESULT: {result}")

            elif pkt_type == 3:  # PKT_BYE
                print("Received PKT_BYE, server rejected result. Exiting...")
                break

            elif pkt_type == 4:  # PKT_FLAG
                flag = data.decode()
                print(f"Received FLAG: {flag}")
                break

if __name__ == "__main__":
    main()
