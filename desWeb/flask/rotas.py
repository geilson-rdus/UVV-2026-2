from flask import Blueprint, jsonify

calculadora_bp = Blueprint('calculadora', __name__)

@calculadora_bp.route('/soma/<float:a>/<float:b>')
def soma(a, b):
    resultado = a + b
    return jsonify({
        "operacao": "soma",
        "a": a,
        "b": b,
        "resultado": resultado
    })

@calculadora_bp.route('/sub/<float:a>/<float:b>')
def subtracao(a, b):
    resultado = a - b
    return jsonify({
        "operacao": "subtracao",
        "a": a,
        "b": b,
        "resultado": resultado
    })

@calculadora_bp.route('/multi/<float:a>/<float:b>')
def multiplicacao(a, b):
    resultado = a * b
    return jsonify({
        "operacao": "multiplicacao",
        "a": a,
        "b": b,
        "resultado": resultado
    })

@calculadora_bp.route('/div/<float:a>/<float:b>')
def divisao(a, b):
    resultado = a / b
    return jsonify({
        "operacao": "divisao",
        "a": a,
        "b": b,
        "resultado": resultado
    })