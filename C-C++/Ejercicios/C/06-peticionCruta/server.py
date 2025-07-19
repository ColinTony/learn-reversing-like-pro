
from http.server import BaseHTTPRequestHandler, HTTPServer

class FlagServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        # Aquí va el contenido con la flag
        response = """
        <html>
          <body>
            <h1>Bienvenido</h1>
            <p>flag{c0l1nr00t_socket_master}</p>
          </body>
        </html>
        """
        self.wfile.write(response.encode())

if __name__ == "__main__":
    host = "0.0.0.0"
    port = 80  # Puedes usar 80 con sudo
    server = HTTPServer((host, port), FlagServer)
    print(f"Servidor corriendo en http://{host}:{port}")
    server.serve_forever()
