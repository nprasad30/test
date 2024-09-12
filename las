# Get the task ARN
task_arn=$(aws ecs list-tasks --cluster talent-site-cluster --service-name talent-site-service --query 'taskArns[0]' --output text)

# Get the ENI ID
eni_id=$(aws ecs describe-tasks --cluster talent-site-cluster --tasks $task_arn --query 'tasks[0].attachments[0].details[?name==`networkInterfaceId`].value' --output text)

# Get the public IP
public_ip=$(aws ec2 describe-network-interfaces --network-interface-ids $eni_id --query 'NetworkInterfaces[0].Association.PublicIp' --output text)

echo "Your talent site is accessible at: http://$public_ip"
