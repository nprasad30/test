#!/bin/bash
yum update -y
yum install -y python3 python3-pip
pip3 install flask

cat <<EOT > /home/ec2-user/app.py
from flask import Flask, request, jsonify
import uuid

app = Flask(__name__)
job_postings = {}

@app.route('/api/post-job', methods=['POST'])
def post_job():
    data = request.json
    if not all(key in data for key in ['job_title', 'company_name', 'job_description']):
        return jsonify({"error": "Missing required fields"}), 400
    
    job_id = str(uuid.uuid4())
    job_postings[job_id] = {
        'id': job_id,
        'title': data['job_title'],
        'company': data['company_name'],
        'description': data['job_description']
    }
    
    return jsonify({
        "message": "Job posted successfully",
        "job_id": job_id
    }), 200

@app.route('/')
def home():
    return "Welcome to the Talent Site!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
EOT

cat <<EOT > /etc/systemd/system/talent-site.service
[Unit]
Description=Talent Site Flask App
After=network.target

[Service]
User=ec2-user
WorkingDirectory=/home/ec2-user
ExecStart=/usr/local/bin/flask run --host=0.0.0.0 --port=80
Restart=always

[Install]
WantedBy=multi-user.target
EOT

systemctl enable talent-site.service
systemctl start talent-site.service
