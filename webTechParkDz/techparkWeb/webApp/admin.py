from django.contrib import admin
from .models import *

admin.site.register(post)
admin.site.register(tag)
admin.site.register(Author)

# Register your models here.
