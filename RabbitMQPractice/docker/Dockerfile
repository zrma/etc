FROM rabbitmq:4.3.2-management

COPY ./init.sh /init.sh
RUN chmod +x /init.sh

# Define default command
CMD ["/init.sh"]
