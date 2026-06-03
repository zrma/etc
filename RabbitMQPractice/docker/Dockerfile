FROM rabbitmq:3.8.5

RUN rabbitmq-plugins enable rabbitmq_management

COPY ./init.sh /init.sh
RUN chmod +x /init.sh

# Define default command
CMD ["/init.sh"]
