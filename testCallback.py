import i_client as ic

def pyAttachCallback(client):
    print('client: ', client)
    return 0

def doit():
    client = ic.buildClient(pyAttachCallback)
