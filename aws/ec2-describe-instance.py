import boto3
client = boto3.client('ec2')

response = client.describe_instances(
	Filters=[
		{
		'Name': 'string',
		'Values': [
			'string',
		]
		},
	],
	InstanceIds=[
		'string',
	],
	DryRun=True|False,
	MaxResults=123,
	NextToken='string'
)

print(response)
