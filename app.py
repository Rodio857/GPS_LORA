from flask import Flask, request, jsonify
from flask_cors import CORS
from datetime import datetime

app = Flask(__name__)
CORS(app)

# Almacén temporal de puntos GPS
puntos = []

@app.route('/api/posicion', methods=['GET'])
def obtener_puntos():
    return jsonify(puntos)

@app.route('/api/posicion', methods=['POST'])
def recibir_posicion():
    data = request.get_json()
    if 'lat' in data and 'lng' in data:
        punto = {
            'lat': data['lat'],
            'lng': data['lng'],
            'timestamp': datetime.now().isoformat()
        }
        puntos.append(punto)
        return jsonify({"status": "ok", "msg": "punto recibido"}), 200
    else:
        return jsonify({"status": "error", "msg": "datos inválidos"}), 400

if __name__ == "__main__":
    app.run(debug=True)
