from django import forms


class UploadFileForm(forms.Form):
    file = forms.ImageField()

class NewPost(forms.Form):
    header = forms.CharField(widget=forms.TextInput(attrs={"class":"form-control"}))
    text = forms.CharField(widget=forms.Textarea(attrs={"class":"form-control"}))
    #tag = forms.CharField(widget=forms.Textarea(attrs={"class":"form-control"}))

def handle_uploaded_file(f):
    with open('static/img/' + f.name, 'wb+') as destination:
        for chunk in f.chunks():
            destination.write(chunk)