'''Nomes dos integrantes: 
Augusto Luiz Marim,
Cauan Pontes Carvalho, 
Geilson Lucas de Souza Silva,
Igor Estevam Gonçalves,
João Pedro Araújo Gonçalves,
Livia Silveira Caldeira,
Lucas Lacerda Freire,
Rhuan Santos Wolfgramm,
Thamily Silva Nogueira,

Listar todos:
curl http://127.0.0.1:3001/api/books

Listar específico por ID: 
curl http://127.0.0.1:3001/api/books/1

Adicionar:
curl.exe --% -X POST -H "Content-Type: application/json" -d "{\"title\":\"O Conde de Monte Cristo\",\"author\":\"Alexandre Dumas\",\"year\":1844,\"available\":true}" http://127.0.0.1:3001/api/books

Deletar:
curl.exe -X DELETE http://127.0.0.1:3001/api/books/2

Adicionar/Atualizar em uma posição específica:
curl.exe --% -X PUT -H "Content-Type: application/json" -d "{\"title\":\"O Assassinato de Roger Ackroyd\",\"author\":\"Agatha Christie\",\"year\":1926,\"available\":true}" http://127.0.0.1:3001/api/books/1
'''

from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlsplit
import json

BOOKS = [
    {
        "id": 1,
        "title": "The Stranger",
        "author": "Albert Camus",
        "year": 1942,
        "available": True
    },
    {
        "id": 2,
        "title": "1984",
        "author": "George Orwell",
        "year": 1949,
        "available": True
    },
    {
        "id": 3,
        "title": "Testemunha Ocular",
        "author": "Agatha Christie",
        "year": 1957,
        "available": True
    }
]

class RestHTTPRequestHandler(BaseHTTPRequestHandler):
    def _send_json(self, status, data=None, headers=None):
        body = b""

        if data is not None:
            body = json.dumps(data).encode("utf-8")
        
        self.send_response(status)
        self.send_header(
            "Content-Type",
            "application/json; charset=utf-8"
        )

        if headers:
            for title, value in headers.items():
                self.send_header(title, value)
        if status != 204:
            self.send_header("Content-Length", str(len(body)))

        self.end_headers()
        if body:
            self.wfile.write(body)
    
    def _get_path(self):
        return urlsplit(self.path).path

    def do_GET(self):
        path = self._get_path()
        if path == "/api/books":
            self._send_json(200, BOOKS)
            return
        
        if path.startswith("/api/books/"):
            book_id_text = path.split("/")[-1]

            try:
                book_id = int(book_id_text)
            except ValueError:
                self._send_json(
                    400,
                    {"error": "Invalid book ID"}
                )

                return

            book = next(
                (book for book in BOOKS if book["id"] == book_id),
                None
            )

            if book is None:
                self._send_json(
                    404,
                    {"error": "Book not found"}
                )
                return

            self._send_json(200, book)
            return

        self._send_json(
            404,
            {"error": "Route not found"}
        )

    def do_POST(self):
        path = self._get_path()
        if path != "/api/books":
            self._send_json(
                404,
                {"error": "Route not found"}
            )

            return

        content_length = self.headers.get("Content-Length")

        if content_length is None:
            self._send_json(
                411,
                {"error": "Content-Length required"}
            )

            return 
        try:
            length = int(content_length)
            data = self.rfile.read(length)
            new_book = json.loads(data)
        except (ValueError, json.JSONDecodeError):
            self._send_json(
                400,
                {"error": "Invalid JSON"}
            )

            return

        if not isinstance(new_book, dict):
            self._send_json(
                400,
                {"error": "JSON object expected"}
            )

            return
        if "title" not in new_book or "author" not in new_book or "year" not in new_book or "available" not in new_book:
            self._send_json(
                400,
                {"error": "Fields 'title', 'author', 'year' and 'available' are required"}
            )
            return

        next_id = max(
            (book["id"] for book in BOOKS),
            default=0
        ) + 1

        new_book["id"] = next_id
        BOOKS.append(new_book)

        self._send_json(
            201,
            new_book,
            headers={
                "Location": f"/api/books/{next_id}"
            }
        )

    def do_DELETE(self):
        path = self._get_path()

        if not path.startswith("/api/books/"):
            self._send_json(
                404,
                {"error": "Route not found"}
            )
            return

        book_id_text = path.split("/")[-1]

        try:
            book_id = int(book_id_text)
        except ValueError:
            self._send_json(
                400,
                {"error": "Invalid book ID"}
            )
            return

        for index, book in enumerate(BOOKS):
            if book["id"] == book_id:
                BOOKS.pop(index)
                self._send_json(204)
                return

        self._send_json(
            404,
            {"error": "Book not found"}
        )

    def do_PUT(self):
        path = self._get_path()

        if not path.startswith("/api/books/"):
            self._send_json(404, {"error": "Route not found"})
            return

        book_id_text = path.split("/")[-1]

        try:
            book_id = int(book_id_text)
        except ValueError:
            self._send_json(400, {"error": "Invalid book ID"})
            return

        book = next((b for b in BOOKS if b["id"] == book_id), None)
        if book is None:
            self._send_json(404, {"error": "Book not found"})
            return

        content_length = self.headers.get("Content-Length")
        if content_length is None:
            self._send_json(411, {"error": "Content-Length required"})
            return

        try:
            length = int(content_length)
            data = self.rfile.read(length)
            updated_data = json.loads(data)
        except (ValueError, json.JSONDecodeError):
            self._send_json(400, {"error": "Invalid JSON"})
            return

        if not isinstance(updated_data, dict):
            self._send_json(400, {"error": "JSON object expected"})
            return
        if "title" not in updated_data or "author" not in updated_data or "year" not in updated_data or "available" not in updated_data:
            self._send_json(400, {"error": "Fields 'title', 'author', 'year' and 'available' are required"})
            return

        book["title"] = updated_data["title"]
        book["author"] = updated_data["author"]
        book["year"] = updated_data["year"]
        book["available"] = updated_data["available"]

        self._send_json(200, book)

def run(
    server_class=HTTPServer,
    handler_class=RestHTTPRequestHandler,
    port=3001
):
    server_address = ("127.0.0.1", port)
    httpd = server_class(server_address, handler_class)

    print(
        f"Servidor HTTP disponivel em "
        f"http://127.0.0.1:{port}"
    )

    httpd.serve_forever()

if __name__ == "__main__":
    run()
