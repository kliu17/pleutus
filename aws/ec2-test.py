import boto3
r = boto3.resource('ec2')
r1 = boto3.resource('s3')

res = r.instances.all()
res1 = r1.instances.all()
for i in res:
	print(i)
for i in res1:
	print(i)
