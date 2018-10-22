#ifndef _SIMPLELOG_LAYOUTAPPENDER_HH
#define _SIMPLELOG_LAYOUTAPPENDER_HH

#include <string>
#include <AppenderSkeleton.h>

namespace SLog {

    /**
     * LayoutAppender is a common superclass for all Appenders that require
     * a Layout. 
     **/
    class LayoutAppender : public AppenderSkeleton {
        public:

        LayoutAppender(const std::string& name);
        virtual ~LayoutAppender();
        
        /**
         * Check if the appender requires a layout. All LayoutAppenders do,
         * therefore this method returns true for all subclasses.
         * 
         * @returns true.
         **/
        virtual bool requiresLayout() const;
        virtual void setLayout(Layout* layout = NULL);

        protected:
        /**
         * Return the layout of the appender.
         * This method is the Layout accessor for subclasses of LayoutAppender.
         * @returns the Layout.
         **/
        Layout& _getLayout();

        private:
        Layout* _layout;
    };
}

#endif // _SIMPLELOG_LAYOUTAPPENDER_HH

