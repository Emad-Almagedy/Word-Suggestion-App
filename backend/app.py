from flask import Flask, request, jsonify
import subprocess
import os
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

@app.route('/get_suggestions', methods=['POST'])
def get_suggestions():
    data = request.get_json()
    word = data.get('word')
    if not word:
        return jsonify({'error': 'No word provided'}), 400

    cpp_executable_path = os.path.join(os.path.dirname(__file__), 'output', 'main.exe')

    # Debug prints to verify paths and file existence
    print(f"Executable path: {cpp_executable_path}")
    if not os.path.exists(cpp_executable_path):
        print(f"Executable does not exist at {cpp_executable_path}")
        return jsonify({'error': 'Executable file not found'}), 500

    try:
        result = subprocess.run([cpp_executable_path, word], capture_output=True, text=True)
        print(f"Subprocess result: {result}")
        if result.returncode != 0:
            return jsonify({'error': 'Error in C++ program execution', 'details': result.stderr}), 500

        return jsonify({'suggestions': result.stdout.strip().split('\n')}), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)
