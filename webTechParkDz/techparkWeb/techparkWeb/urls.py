"""techparkWeb URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.urls import re_path
from webApp.views import showIndex 
from django.urls import include
from webApp.views import *
urlpatterns = [
    path('admin/', admin.site.urls),
    re_path(r'^\d*$', showIndex, name = 'index'),
    path('login/',  showLogin, name= 'login'),
    re_path(r'^template/.*.html$',  getHtmlDoc, name ='getdoc' ),
    path("register/", showReg, name= 'register'),
    path("tag/<str:req_tag>", getByTag, name='tag' ),
    path("posts/<int:id>", getOnePost, name="posts"),
    path('alltags/',  showTags, name= 'alltags'),
    path('newpost/',addNewPost, name= 'newpost'),
    path('profile/', showProfile, name= 'profile'),
    path('logout/', logOut, name= 'logout')
  
]


