from django.conf import settings
from django.db import models
from django.contrib.auth.models import User
from django.dispatch import receiver
from django.db.models.signals import post_save
class tag(models.Model):
    text =  models.TextField(max_length =30)
    def __str__(self):
        return self.text

    class Meta:
        db_table = ''
        managed = True
        verbose_name = 'tag'
        verbose_name_plural = 'tags'


class mark(models.Model):
    positive = models.BooleanField()
    who = models.ForeignKey('Author', on_delete= models.CASCADE)

class QuestionManager(models.Manager):
    def hot(self):
        return self.order_by('-id')

class post(models.Model):
    def __str__(self):
        return self.header
    
    author =  models.ForeignKey(
        'Author', on_delete=models.CASCADE, blank=True, null=True
    )
    header = models.TextField(max_length = 300)
    text= models.TextField(max_length=2000, help_text="text post")
    tags = models.ManyToManyField('tag', blank=True, related_name='posts')
    raiting = models.ManyToManyField('mark')
    intRaiting = models.IntegerField(default=0)
    def countRaiting(self):
        for m in  self.raiting:
            if m.positive:
             self.intRaiting +=1
            else:
                self.intRaiting -= 1
    class Meta:
        db_table = ''
        managed = True
        verbose_name = 'post'
        verbose_name_plural = 'posts'
    objects = QuestionManager() 



class Author(models.Model):
    user = models.OneToOneField(
        User,
        on_delete=models.CASCADE,
        primary_key=True,
        unique = True,
    )
    rating = models.IntegerField()
    img = models.ImageField(default = '/img/avatar/default.png', upload_to = 'static/img')
    def __str__(self):
        return self.user.username
    class Meta:
        db_table = ''
        managed = True
        verbose_name = 'Author'
        verbose_name_plural = 'Author'



@receiver(post_save, sender=User)
def create_user_profile(sender, instance, created, **kwargs):
    if created:
        Author.objects.create(user = instance)



@receiver (post_save, sender = User)
def save_user_prifile(sender, instance, **kwargs):
    instance.author.save()
    

    


