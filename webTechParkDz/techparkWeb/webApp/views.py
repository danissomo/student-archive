from django.shortcuts import render
from django.db import models
from .models import *
from .modelsController import *
import re
from django.shortcuts import get_object_or_404
from django.contrib.auth import logout
from django.contrib.auth import login
from django.contrib.auth import authenticate
from django.shortcuts import redirect
from django.shortcuts import redirect
from .forms import *
from django.core.files.storage import FileSystemStorage
def addTemplateFields(is_paginated = bool):
    context = {}
    if(is_paginated):
        context.update({'is_paginated': 'true'})
    context.update({'besttags': tag.objects.all()[0:9]})
    return context

def showIndex(request ):
    context = addTemplateFields(is_paginated  = True)
    pg = pagination()
    objList, ArrayOfNum  = pg.paginate(post.objects.all(), request.path)
    context.update({'questions': objList })
    context.update({'navButtons': ArrayOfNum })
    return render(request, 'index.html', context)


def getHtmlDoc(request):
    urlPath = request.path_info
    urlPath = urlPath.replace("/import/", "")
    return render(request, urlPath  )


def showLogin(request):
    if request.method == 'POST':
        
        if request.POST.get('email'):
                user = authenticate(request, username = request.POST.get('email'), 
                password = request.POST.get('password'))
                if user is not None:
                    login(request, user)
                    return redirect('index')
    context=addTemplateFields(False)
    
    return render(request, 'login.html', context)


def showReg(request):
    context=addTemplateFields(False)

    return render(request, 'register.html', context)

def getByTag(request, req_tag):
    context = addTemplateFields(False)
    postsbytag =  tag.objects.all().filter(text = req_tag)[0].posts.all()
    context.update({ 'questions': postsbytag }) 
    context.update({'filtredtag':req_tag}) 
    return render(request, 'filterByTag.html',  context)

def getOnePost(request, id):
    context = addTemplateFields(False)
    context.update({'questions': [post.objects.all()[id]]})
    return render(request, 'index.html', context)

def showTags(request ):
    context = addTemplateFields(False)
    context.update({'tags':tag.objects.all()})
    return render(request, 'allTags.html', context)


def addNewPost(request):
    if request.user.is_authenticated:
        if request.method == 'POST':
            form = NewPost(request.POST)
            if form.is_valid():
                print(1)
                newpost = post( )
                newpost.author = request.user.author
                newpost.header = form['header']
                newpost.text = form['text']
                newpost.save()
        else: 
            form =NewPost()
        return render(request, 'newPost.html', {'form': form})
    else:
        return render(request, 'login.html')


def showProfile(request):
    if request.user.is_authenticated:
       
        if request.method == 'POST':
            nick = request.POST.get('nickname')
            email = request.POST.get('email')
            pas = request.POST.get('password')
            if nick is not None:
                request.user.username= nick
            if email is not None:
                request.user.email = email
            if pas is not None:
                request.user.password = pas
            form = UploadFileForm(request.POST,request.FILES)
            print(form)
            if form.is_valid():
                handle_uploaded_file(request.FILES['file'])
                request.user.author.img = request.FILES['file']
                request.user.author.save()
        else :
            form = UploadFileForm()

        return render(request, 'profile.html', {'form' : form})
            
    else :
        return render(request, 'login.html')

def logOut(request):
    if request.user.is_authenticated:
        logout(request)
    return render(request, 'index.html')


def likerequest(request):
    if request.user.is_authenticated:
        return